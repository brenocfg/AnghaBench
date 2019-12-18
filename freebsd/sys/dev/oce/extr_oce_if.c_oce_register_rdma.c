#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int num_vectors; int start_vector; int /*<<< orphan*/ * vector_list; } ;
struct oce_dev_info {int db_page_size; scalar_t__ intr_mode; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  vendor_id; int /*<<< orphan*/  mac_addr; TYPE_1__ msix; int /*<<< orphan*/  dev_family; int /*<<< orphan*/  db_btag; int /*<<< orphan*/  db_bhandle; int /*<<< orphan*/  ifp; TYPE_4__* softc; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  di ;
struct TYPE_16__ {scalar_t__ size; int /*<<< orphan*/  (* announce ) (struct oce_dev_info*) ;} ;
struct TYPE_15__ {scalar_t__ size; int /*<<< orphan*/  get_mac_addr; int /*<<< orphan*/  common_req_hdr_init; int /*<<< orphan*/  mbox_post; int /*<<< orphan*/  close; } ;
struct TYPE_13__ {int /*<<< orphan*/  mac_addr; } ;
struct TYPE_14__ {int flags; int intr_count; int roce_intr_count; int rdma_flags; struct TYPE_14__* next; int /*<<< orphan*/  dev; TYPE_3__ macaddr; TYPE_2__* intrs; int /*<<< orphan*/  db_btag; int /*<<< orphan*/  db_bhandle; int /*<<< orphan*/  ifp; } ;
struct TYPE_12__ {int /*<<< orphan*/  vector; } ;
typedef  TYPE_4__* POCE_SOFTC ;
typedef  TYPE_5__* POCE_RDMA_INFO ;
typedef  TYPE_6__* POCE_RDMA_IF ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int OCE_FLAGS_USING_MSI ; 
 int OCE_FLAGS_USING_MSIX ; 
 int /*<<< orphan*/  OCE_GEN2_FAMILY ; 
 scalar_t__ OCE_INTERRUPT_MODE_INTX ; 
 scalar_t__ OCE_INTERRUPT_MODE_MSI ; 
 scalar_t__ OCE_INTERRUPT_MODE_MSIX ; 
 int OCE_RDMA_FLAG_SUPPORTED ; 
 scalar_t__ OCE_RDMA_IF_SIZE ; 
 int /*<<< orphan*/  OCE_RDMA_INFO_RDMA_SUPPORTED ; 
 scalar_t__ OCE_RDMA_INFO_SIZE ; 
 int /*<<< orphan*/  mbx_common_req_hdr_init ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct oce_dev_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oce_get_mac_addr ; 
 int /*<<< orphan*/  oce_mbox_post ; 
 int /*<<< orphan*/  oce_rdma_close ; 
 TYPE_6__* oce_rdma_if ; 
 int /*<<< orphan*/  pci_get_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_vendor (int /*<<< orphan*/ ) ; 
 TYPE_4__* softc_head ; 
 int /*<<< orphan*/  stub1 (struct oce_dev_info*) ; 

int
oce_register_rdma(POCE_RDMA_INFO rdma_info, POCE_RDMA_IF rdma_if)
{
  POCE_SOFTC sc;
  struct oce_dev_info di;
  int i;

  if ((rdma_info == NULL) || (rdma_if == NULL)) {
    return -EINVAL;
  }

  if ((rdma_info->size != OCE_RDMA_INFO_SIZE) ||
      (rdma_if->size != OCE_RDMA_IF_SIZE)) {
    return -ENXIO;
  }

  rdma_info->close = oce_rdma_close;
  rdma_info->mbox_post = oce_mbox_post;
  rdma_info->common_req_hdr_init = mbx_common_req_hdr_init;
  rdma_info->get_mac_addr = oce_get_mac_addr;

  oce_rdma_if = rdma_if;

  sc = softc_head;
  while (sc != NULL) {
    if (oce_rdma_if->announce != NULL) {
      memset(&di, 0, sizeof(di));
      di.dev = sc->dev;
      di.softc = sc;
      di.ifp = sc->ifp;
      di.db_bhandle = sc->db_bhandle;
      di.db_btag = sc->db_btag;
      di.db_page_size = 4096;
      if (sc->flags & OCE_FLAGS_USING_MSIX) {
        di.intr_mode = OCE_INTERRUPT_MODE_MSIX;
      } else if (sc->flags & OCE_FLAGS_USING_MSI) {
        di.intr_mode = OCE_INTERRUPT_MODE_MSI;
      } else {
        di.intr_mode = OCE_INTERRUPT_MODE_INTX;
      }
      di.dev_family = OCE_GEN2_FAMILY; // fixme: must detect skyhawk
      if (di.intr_mode != OCE_INTERRUPT_MODE_INTX) {
        di.msix.num_vectors = sc->intr_count + sc->roce_intr_count;
        di.msix.start_vector = sc->intr_count;
        for (i=0; i<di.msix.num_vectors; i++) {
          di.msix.vector_list[i] = sc->intrs[i].vector;
        }
      } else {
      }
      memcpy(di.mac_addr, sc->macaddr.mac_addr, 6);
      di.vendor_id = pci_get_vendor(sc->dev);
      di.dev_id = pci_get_device(sc->dev);

      if (sc->rdma_flags & OCE_RDMA_FLAG_SUPPORTED) {
          di.flags  |= OCE_RDMA_INFO_RDMA_SUPPORTED;
      }

      rdma_if->announce(&di);
      sc = sc->next;
    }
  }

  return 0;
}