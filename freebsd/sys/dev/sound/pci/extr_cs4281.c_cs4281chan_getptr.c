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
typedef  int u_int32_t ;
struct sc_info {int dummy; } ;
struct sc_chinfo {int /*<<< orphan*/  dma_chan; int /*<<< orphan*/  buffer; struct sc_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS4281PCI_DBA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS4281PCI_DCA (int /*<<< orphan*/ ) ; 
 int cs4281_rd (struct sc_info*,int /*<<< orphan*/ ) ; 
 int sndbuf_getsize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
cs4281chan_getptr(kobj_t obj, void *data)
{
    struct sc_chinfo *ch = data;
    struct sc_info *sc = ch->parent;
    u_int32_t  dba, dca, ptr;
    int sz;

    sz  = sndbuf_getsize(ch->buffer);
    dba = cs4281_rd(sc, CS4281PCI_DBA(ch->dma_chan));
    dca = cs4281_rd(sc, CS4281PCI_DCA(ch->dma_chan));
    ptr = (dca - dba + sz) % sz;

    return ptr;
}