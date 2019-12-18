#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cis1_info; int /*<<< orphan*/  product; int /*<<< orphan*/  manufacturer; } ;
struct pccard_softc {TYPE_1__ card; } ;
struct pccard_ivar {struct pccard_function* pf; } ;
struct pccard_function {int /*<<< orphan*/  function; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct pccard_ivar* PCCARD_IVAR (int /*<<< orphan*/ ) ; 
 struct pccard_softc* PCCARD_SOFTC (int /*<<< orphan*/ ) ; 
 int SBUF_FIXEDLEN ; 
 int SBUF_INCLUDENUL ; 
 int /*<<< orphan*/  devctl_safe_quote_sb (struct sbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,size_t,int) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 

__attribute__((used)) static int
pccard_child_pnpinfo_str(device_t bus, device_t child, char *buf,
    size_t buflen)
{
	struct pccard_ivar *devi = PCCARD_IVAR(child);
	struct pccard_function *pf = devi->pf;
	struct pccard_softc *sc = PCCARD_SOFTC(bus);
	struct sbuf sb;

	sbuf_new(&sb, buf, buflen, SBUF_FIXEDLEN | SBUF_INCLUDENUL);
	sbuf_printf(&sb, "manufacturer=0x%04x product=0x%04x "
	    "cisvendor=\"", sc->card.manufacturer, sc->card.product);
	devctl_safe_quote_sb(&sb, sc->card.cis1_info[0]);
	sbuf_printf(&sb, "\" cisproduct=\"");
	devctl_safe_quote_sb(&sb, sc->card.cis1_info[1]);
	sbuf_printf(&sb, "\" function_type=%d", pf->function);
	sbuf_finish(&sb);
	sbuf_delete(&sb);

	return (0);
}