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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ah ; 
 scalar_t__ dump_deviceids_pci () ; 
 scalar_t__ dump_deviceids_pcmcia () ; 
 scalar_t__ dump_deviceids_usb () ; 
 int /*<<< orphan*/  dump_regvals () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ofp ; 
 int /*<<< orphan*/  rh ; 
 int /*<<< orphan*/  sh ; 
 int /*<<< orphan*/ * yyin ; 
 int /*<<< orphan*/  yyparse () ; 

int
inf_parse (FILE *fp, FILE *outfp)
{
	TAILQ_INIT(&sh);
	TAILQ_INIT(&rh);
	TAILQ_INIT(&ah);

	ofp = outfp;
	yyin = fp;
	yyparse();

	if (dump_deviceids_pci() == 0 &&
	    dump_deviceids_pcmcia() == 0 &&
	    dump_deviceids_usb() == 0)
		return (-1);

	fprintf(outfp, "#ifdef NDIS_REGVALS\n");
	dump_regvals();
	fprintf(outfp, "#endif /* NDIS_REGVALS */\n");

	return (0);
}