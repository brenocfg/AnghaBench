#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {void* len0; void* len1; void* len2; void* len3; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct sglist_component {void* ptr0; TYPE_2__ u; void* ptr1; void* ptr2; void* ptr3; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cpt_vf {struct pci_dev* pdev; } ;
struct buf_ptr {scalar_t__ dma_addr; int /*<<< orphan*/  size; int /*<<< orphan*/  vptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EFAULT ; 
 int EIO ; 
 void* cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int setup_sgio_components(struct cpt_vf *cptvf, struct buf_ptr *list,
				 int buf_count, u8 *buffer)
{
	int ret = 0, i, j;
	int components;
	struct sglist_component *sg_ptr = NULL;
	struct pci_dev *pdev = cptvf->pdev;

	if (unlikely(!list)) {
		dev_err(&pdev->dev, "Input List pointer is NULL\n");
		return -EFAULT;
	}

	for (i = 0; i < buf_count; i++) {
		if (likely(list[i].vptr)) {
			list[i].dma_addr = dma_map_single(&pdev->dev,
							  list[i].vptr,
							  list[i].size,
							  DMA_BIDIRECTIONAL);
			if (unlikely(dma_mapping_error(&pdev->dev,
						       list[i].dma_addr))) {
				dev_err(&pdev->dev, "DMA map kernel buffer failed for component: %d\n",
					i);
				ret = -EIO;
				goto sg_cleanup;
			}
		}
	}

	components = buf_count / 4;
	sg_ptr = (struct sglist_component *)buffer;
	for (i = 0; i < components; i++) {
		sg_ptr->u.s.len0 = cpu_to_be16(list[i * 4 + 0].size);
		sg_ptr->u.s.len1 = cpu_to_be16(list[i * 4 + 1].size);
		sg_ptr->u.s.len2 = cpu_to_be16(list[i * 4 + 2].size);
		sg_ptr->u.s.len3 = cpu_to_be16(list[i * 4 + 3].size);
		sg_ptr->ptr0 = cpu_to_be64(list[i * 4 + 0].dma_addr);
		sg_ptr->ptr1 = cpu_to_be64(list[i * 4 + 1].dma_addr);
		sg_ptr->ptr2 = cpu_to_be64(list[i * 4 + 2].dma_addr);
		sg_ptr->ptr3 = cpu_to_be64(list[i * 4 + 3].dma_addr);
		sg_ptr++;
	}

	components = buf_count % 4;

	switch (components) {
	case 3:
		sg_ptr->u.s.len2 = cpu_to_be16(list[i * 4 + 2].size);
		sg_ptr->ptr2 = cpu_to_be64(list[i * 4 + 2].dma_addr);
		/* Fall through */
	case 2:
		sg_ptr->u.s.len1 = cpu_to_be16(list[i * 4 + 1].size);
		sg_ptr->ptr1 = cpu_to_be64(list[i * 4 + 1].dma_addr);
		/* Fall through */
	case 1:
		sg_ptr->u.s.len0 = cpu_to_be16(list[i * 4 + 0].size);
		sg_ptr->ptr0 = cpu_to_be64(list[i * 4 + 0].dma_addr);
		break;
	default:
		break;
	}

	return ret;

sg_cleanup:
	for (j = 0; j < i; j++) {
		if (list[j].dma_addr) {
			dma_unmap_single(&pdev->dev, list[i].dma_addr,
					 list[i].size, DMA_BIDIRECTIONAL);
		}

		list[j].dma_addr = 0;
	}

	return ret;
}