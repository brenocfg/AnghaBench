#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  fwip_ifp; } ;
struct TYPE_7__ {scalar_t__ lo; scalar_t__ hi; } ;
struct TYPE_6__ {TYPE_1__* fc; } ;
struct fwip_softc {TYPE_4__ fw_softc; TYPE_3__ last_dest; int /*<<< orphan*/  ver6; int /*<<< orphan*/  unit6; int /*<<< orphan*/  spec6; int /*<<< orphan*/  ver4; int /*<<< orphan*/  unit4; int /*<<< orphan*/  spec4; TYPE_2__ fd; } ;
struct crom_src {int dummy; } ;
struct crom_chunk {int dummy; } ;
struct TYPE_5__ {struct crom_chunk* crom_root; struct crom_src* crom_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  CROM_UDIR ; 
 int /*<<< orphan*/  CSRKEY_SPEC ; 
 int /*<<< orphan*/  CSRKEY_VER ; 
 int CSRVAL_IETF ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  crom_add_chunk (struct crom_src*,struct crom_chunk*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crom_add_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  crom_add_simple_text (struct crom_src*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  firewire_busreset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fwip_post_busreset(void *arg)
{
	struct fwip_softc *fwip = arg;
	struct crom_src *src;
	struct crom_chunk *root;

	src = fwip->fd.fc->crom_src;
	root = fwip->fd.fc->crom_root;

	/* RFC2734 IPv4 over IEEE1394 */
	bzero(&fwip->unit4, sizeof(struct crom_chunk));
	crom_add_chunk(src, root, &fwip->unit4, CROM_UDIR);
	crom_add_entry(&fwip->unit4, CSRKEY_SPEC, CSRVAL_IETF);
	crom_add_simple_text(src, &fwip->unit4, &fwip->spec4, "IANA");
	crom_add_entry(&fwip->unit4, CSRKEY_VER, 1);
	crom_add_simple_text(src, &fwip->unit4, &fwip->ver4, "IPv4");

	/* RFC3146 IPv6 over IEEE1394 */
	bzero(&fwip->unit6, sizeof(struct crom_chunk));
	crom_add_chunk(src, root, &fwip->unit6, CROM_UDIR);
	crom_add_entry(&fwip->unit6, CSRKEY_SPEC, CSRVAL_IETF);
	crom_add_simple_text(src, &fwip->unit6, &fwip->spec6, "IANA");
	crom_add_entry(&fwip->unit6, CSRKEY_VER, 2);
	crom_add_simple_text(src, &fwip->unit6, &fwip->ver6, "IPv6");

	fwip->last_dest.hi = 0;
	fwip->last_dest.lo = 0;
	firewire_busreset(fwip->fw_softc.fwip_ifp);
}