#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_dev {int dummy; } ;
struct nitrox_q_vector {int ring; int valid; int /*<<< orphan*/  resp_tasklet; int /*<<< orphan*/  name; struct nitrox_device* ndev; int /*<<< orphan*/ * cmdq; } ;
struct nitrox_device {int num_vecs; int nr_queues; struct nitrox_q_vector* qvec; int /*<<< orphan*/ * pkt_inq; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV (struct nitrox_device*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQ_NAMESZ ; 
 int NON_RING_MSIX_BASE ; 
 int NR_RING_VECTORS ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int PKT_RING_MSIX_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  get_cpu_mask (int) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int,int /*<<< orphan*/ ) ; 
 struct nitrox_q_vector* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitrox_unregister_interrupts (struct nitrox_device*) ; 
 int /*<<< orphan*/  nps_core_int_isr ; 
 int /*<<< orphan*/  nps_core_int_tasklet ; 
 int /*<<< orphan*/  nps_pkt_slc_isr ; 
 int num_online_cpus () ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int pci_irq_vector (struct pci_dev*,int) ; 
 int pci_msix_vec_count (struct pci_dev*) ; 
 int /*<<< orphan*/  pkt_slc_resp_tasklet ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nitrox_q_vector*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

int nitrox_register_interrupts(struct nitrox_device *ndev)
{
	struct pci_dev *pdev = ndev->pdev;
	struct nitrox_q_vector *qvec;
	int nr_vecs, vec, cpu;
	int ret, i;

	/*
	 * PF MSI-X vectors
	 *
	 * Entry 0: NPS PKT ring 0
	 * Entry 1: AQMQ ring 0
	 * Entry 2: ZQM ring 0
	 * Entry 3: NPS PKT ring 1
	 * Entry 4: AQMQ ring 1
	 * Entry 5: ZQM ring 1
	 * ....
	 * Entry 192: NPS_CORE_INT_ACTIVE
	 */
	nr_vecs = pci_msix_vec_count(pdev);

	/* Enable MSI-X */
	ret = pci_alloc_irq_vectors(pdev, nr_vecs, nr_vecs, PCI_IRQ_MSIX);
	if (ret < 0) {
		dev_err(DEV(ndev), "msix vectors %d alloc failed\n", nr_vecs);
		return ret;
	}
	ndev->num_vecs = nr_vecs;

	ndev->qvec = kcalloc(nr_vecs, sizeof(*qvec), GFP_KERNEL);
	if (!ndev->qvec) {
		pci_free_irq_vectors(pdev);
		return -ENOMEM;
	}

	/* request irqs for packet rings/ports */
	for (i = PKT_RING_MSIX_BASE; i < (nr_vecs - 1); i += NR_RING_VECTORS) {
		qvec = &ndev->qvec[i];

		qvec->ring = i / NR_RING_VECTORS;
		if (qvec->ring >= ndev->nr_queues)
			break;

		qvec->cmdq = &ndev->pkt_inq[qvec->ring];
		snprintf(qvec->name, IRQ_NAMESZ, "nitrox-pkt%d", qvec->ring);
		/* get the vector number */
		vec = pci_irq_vector(pdev, i);
		ret = request_irq(vec, nps_pkt_slc_isr, 0, qvec->name, qvec);
		if (ret) {
			dev_err(DEV(ndev), "irq failed for pkt ring/port%d\n",
				qvec->ring);
			goto irq_fail;
		}
		cpu = qvec->ring % num_online_cpus();
		irq_set_affinity_hint(vec, get_cpu_mask(cpu));

		tasklet_init(&qvec->resp_tasklet, pkt_slc_resp_tasklet,
			     (unsigned long)qvec);
		qvec->valid = true;
	}

	/* request irqs for non ring vectors */
	i = NON_RING_MSIX_BASE;
	qvec = &ndev->qvec[i];
	qvec->ndev = ndev;

	snprintf(qvec->name, IRQ_NAMESZ, "nitrox-core-int%d", i);
	/* get the vector number */
	vec = pci_irq_vector(pdev, i);
	ret = request_irq(vec, nps_core_int_isr, 0, qvec->name, qvec);
	if (ret) {
		dev_err(DEV(ndev), "irq failed for nitrox-core-int%d\n", i);
		goto irq_fail;
	}
	cpu = num_online_cpus();
	irq_set_affinity_hint(vec, get_cpu_mask(cpu));

	tasklet_init(&qvec->resp_tasklet, nps_core_int_tasklet,
		     (unsigned long)qvec);
	qvec->valid = true;

	return 0;

irq_fail:
	nitrox_unregister_interrupts(ndev);
	return ret;
}