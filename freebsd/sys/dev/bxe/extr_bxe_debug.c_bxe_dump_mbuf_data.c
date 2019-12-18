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
struct mbuf {int* m_data; int m_len; struct mbuf* m_next; } ;
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
bxe_dump_mbuf_data(struct bxe_softc *sc,
                   char             *tag,
                   struct mbuf      *m,
                   uint8_t          contents)
{
    char buf[256];
    char c[32];
    uint8_t *memp;
    int i, xx = 0;

    mtx_lock(&bxe_prev_mtx);

    BLOGI(sc, "++++++++++++ %s\n", tag);

    while (m)
    {
        memp = m->m_data;
        strcpy(buf, "** > ");
        snprintf(c, sizeof(c), "%03x", xx);
        strcat(buf, c);
        strcat(buf, ": ");

        if (contents)
        {
            for (i = 0; i < m->m_len; i++)
            {
                if ((xx != 0) && (xx % 16 == 0))
                {
                    BLOGI(sc, "%s\n", buf);
                    strcpy(buf, "**   ");
                    snprintf(c, sizeof(c), "%03x", xx);
                    strcat(buf, c);
                    strcat(buf, ": ");
                }

                snprintf(c, sizeof(c), "%02x ", *memp);
                strcat(buf, c);

                memp++;
                xx++;
            }
        }
        else
        {
            snprintf(c, sizeof(c), "%d", m->m_len);
            strcat(buf, c);
            xx += m->m_len;
        }

        BLOGI(sc, "%s\n", buf);
        m = m->m_next;
    }

    BLOGI(sc, "------------ %s\n", tag);

    mtx_unlock(&bxe_prev_mtx);
}