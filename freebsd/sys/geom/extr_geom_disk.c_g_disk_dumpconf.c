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
struct sbuf {int dummy; } ;
struct g_provider {int dummy; } ;
struct g_geom {struct g_disk_softc* softc; } ;
struct g_disk_softc {struct disk* dp; } ;
struct g_consumer {int dummy; } ;
struct disk {char const* d_fwheads; char const* d_fwsectors; char const* d_rotation_rate; int (* d_getattr ) (struct bio*) ;char* d_ident; char* d_descr; } ;
struct bio {char* bio_attribute; char* bio_data; void* bio_length; struct disk* bio_disk; } ;

/* Variables and functions */
 void* DISK_IDENT_SIZE ; 
 char const* DISK_RR_MAX ; 
 char const* DISK_RR_MIN ; 
 char const* DISK_RR_NON_ROTATING ; 
 char const* DISK_RR_UNKNOWN ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct bio* g_alloc_bio () ; 
 int /*<<< orphan*/  g_conf_cat_escaped (struct sbuf*,char*) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_malloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_cat (struct sbuf*,char*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,char const*,...) ; 
 int stub1 (struct bio*) ; 
 int stub2 (struct bio*) ; 
 int stub3 (struct bio*) ; 

__attribute__((used)) static void
g_disk_dumpconf(struct sbuf *sb, const char *indent, struct g_geom *gp, struct g_consumer *cp, struct g_provider *pp)
{
	struct bio *bp;
	struct disk *dp;
	struct g_disk_softc *sc;
	char *buf;
	int res = 0;

	sc = gp->softc;
	if (sc == NULL || (dp = sc->dp) == NULL)
		return;
	if (indent == NULL) {
		sbuf_printf(sb, " hd %u", dp->d_fwheads);
		sbuf_printf(sb, " sc %u", dp->d_fwsectors);
		return;
	}
	if (pp != NULL) {
		sbuf_printf(sb, "%s<fwheads>%u</fwheads>\n",
		    indent, dp->d_fwheads);
		sbuf_printf(sb, "%s<fwsectors>%u</fwsectors>\n",
		    indent, dp->d_fwsectors);

		/*
		 * "rotationrate" is a little complicated, because the value
		 * returned by the drive might not be the RPM; 0 and 1 are
		 * special cases, and there's also a valid range.
		 */
		sbuf_printf(sb, "%s<rotationrate>", indent);
		if (dp->d_rotation_rate == DISK_RR_UNKNOWN) /* Old drives */
			sbuf_cat(sb, "unknown");	/* don't report RPM. */
		else if (dp->d_rotation_rate == DISK_RR_NON_ROTATING)
			sbuf_cat(sb, "0");
		else if ((dp->d_rotation_rate >= DISK_RR_MIN) &&
		    (dp->d_rotation_rate <= DISK_RR_MAX))
			sbuf_printf(sb, "%u", dp->d_rotation_rate);
		else
			sbuf_cat(sb, "invalid");
		sbuf_cat(sb, "</rotationrate>\n");
		if (dp->d_getattr != NULL) {
			buf = g_malloc(DISK_IDENT_SIZE, M_WAITOK);
			bp = g_alloc_bio();
			bp->bio_disk = dp;
			bp->bio_attribute = "GEOM::ident";
			bp->bio_length = DISK_IDENT_SIZE;
			bp->bio_data = buf;
			res = dp->d_getattr(bp);
			sbuf_printf(sb, "%s<ident>", indent);
			g_conf_cat_escaped(sb, res == 0 ? buf : dp->d_ident);
			sbuf_cat(sb, "</ident>\n");
			bp->bio_attribute = "GEOM::lunid";
			bp->bio_length = DISK_IDENT_SIZE;
			bp->bio_data = buf;
			if (dp->d_getattr(bp) == 0) {
				sbuf_printf(sb, "%s<lunid>", indent);
				g_conf_cat_escaped(sb, buf);
				sbuf_cat(sb, "</lunid>\n");
			}
			bp->bio_attribute = "GEOM::lunname";
			bp->bio_length = DISK_IDENT_SIZE;
			bp->bio_data = buf;
			if (dp->d_getattr(bp) == 0) {
				sbuf_printf(sb, "%s<lunname>", indent);
				g_conf_cat_escaped(sb, buf);
				sbuf_cat(sb, "</lunname>\n");
			}
			g_destroy_bio(bp);
			g_free(buf);
		} else {
			sbuf_printf(sb, "%s<ident>", indent);
			g_conf_cat_escaped(sb, dp->d_ident);
			sbuf_cat(sb, "</ident>\n");
		}
		sbuf_printf(sb, "%s<descr>", indent);
		g_conf_cat_escaped(sb, dp->d_descr);
		sbuf_cat(sb, "</descr>\n");
	}
}