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
struct mn_softc {int framing; scalar_t__ nhooks; char* nodename; } ;
typedef  int /*<<< orphan*/  node_p ;
typedef  enum framing { ____Placeholder_framing } framing ;

/* Variables and functions */
 int E1 ; 
 int E1U ; 
 struct mn_softc* NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f54_init (struct mn_softc*) ; 
 int /*<<< orphan*/  mn_reset (struct mn_softc*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void
ngmn_config(node_p node, char *set, char *ret)
{
	struct mn_softc *sc;
	enum framing wframing;

	sc = NG_NODE_PRIVATE(node);

	if (set != NULL) {
		if (!strncmp(set, "line ", 5)) {
			wframing = sc->framing;
			if (!strcmp(set, "line e1")) {
				wframing = E1;
			} else if (!strcmp(set, "line e1u")) {
				wframing = E1U;
			} else {
				strcat(ret, "ENOGROK\n");
				return;
			}
			if (wframing == sc->framing)
				return;
			if (sc->nhooks > 0) {
				sprintf(ret, "Cannot change line when %d hooks open\n", sc->nhooks);
				return;
			}
			sc->framing = wframing;
#if 1
			f54_init(sc);
#else
			mn_reset(sc);
#endif
		} else {
			printf("%s CONFIG SET [%s]\n", sc->nodename, set);
			strcat(ret, "ENOGROK\n");
			return;
		}
	}
	
}