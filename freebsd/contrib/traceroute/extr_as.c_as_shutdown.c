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
struct aslookup {scalar_t__ as_debug; scalar_t__ as_f; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  free (struct aslookup*) ; 

void
as_shutdown(void *_asn)
{
	struct aslookup *asn = _asn;

	(void)fprintf(asn->as_f, "!q\n");
	(void)fclose(asn->as_f);

#ifdef AS_DEBUG_FILE
	if (asn->as_debug) {
		(void)fprintf(asn->as_debug, ">> !q\n");
		(void)fclose(asn->as_debug);
	}
#endif /* AS_DEBUG_FILE */

	free(asn);
}