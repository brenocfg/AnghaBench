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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGI (struct bxe_softc*,char*,char*) ; 
 int /*<<< orphan*/  bxe_prev_mtx ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

void
bxe_dump_mem(struct bxe_softc *sc,
             char             *tag,
             uint8_t          *mem,
             uint32_t         len)
{
    char buf[256];
    char c[32];
    int  xx;

    mtx_lock(&bxe_prev_mtx);

    BLOGI(sc, "++++++++++++ %s\n", tag);
    strcpy(buf, "** 000: ");

    for (xx = 0; xx < len; xx++)
    {
        if ((xx != 0) && (xx % 16 == 0))
        {
            BLOGI(sc, "%s\n", buf);
            strcpy(buf, "** ");
            snprintf(c, sizeof(c), "%03x", xx);
            strcat(buf, c);
            strcat(buf, ": ");
        }

        snprintf(c, sizeof(c), "%02x ", *mem);
        strcat(buf, c);

        mem++;
    }

    BLOGI(sc, "%s\n", buf);
    BLOGI(sc, "------------ %s\n", tag);

    mtx_unlock(&bxe_prev_mtx);
}