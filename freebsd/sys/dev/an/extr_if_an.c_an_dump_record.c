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
typedef  int u_int8_t ;
struct an_softc {int /*<<< orphan*/  an_ifp; } ;
struct an_ltv_gen {int an_len; int an_type; int /*<<< orphan*/  an_val; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int an_dump ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ isprint (char) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
an_dump_record(struct an_softc *sc, struct an_ltv_gen *ltv, char *string)
{
	u_int8_t		*ptr2;
	int			len;
	int			i;
	int			count = 0;
	char			buf[17], temp;

	len = ltv->an_len - 4;
	if_printf(sc->an_ifp, "RID %4x, Length %4d, Mode %s\n",
		ltv->an_type, ltv->an_len - 4, string);

	if (an_dump == 1 || (an_dump == ltv->an_type)) {
		if_printf(sc->an_ifp, "\t");
		bzero(buf,sizeof(buf));

		ptr2 = (u_int8_t *)&ltv->an_val;
		for (i = len; i > 0; i--) {
			printf("%02x ", *ptr2);

			temp = *ptr2++;
			if (isprint(temp))
				buf[count] = temp;
			else
				buf[count] = '.';
			if (++count == 16) {
				count = 0;
				printf("%s\n",buf);
				if_printf(sc->an_ifp, "\t");
				bzero(buf,sizeof(buf));
			}
		}
		for (; count != 16; count++) {
			printf("   ");
		}
		printf(" %s\n",buf);
	}
}