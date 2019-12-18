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
typedef  size_t u_int ;
struct ahd_softc {void** sysctl_tree; int /*<<< orphan*/ * sysctl_ctx; int /*<<< orphan*/ * summerr; int /*<<< orphan*/  dev_softc; } ;

/* Variables and functions */
 size_t AHD_ERRORS_CORRECTABLE ; 
 size_t AHD_ERRORS_NUMBER ; 
 size_t AHD_SYSCTL_DEBUG ; 
 size_t AHD_SYSCTL_NUMBER ; 
 size_t AHD_SYSCTL_ROOT ; 
 size_t AHD_SYSCTL_SUMMARY ; 
 int /*<<< orphan*/  CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_UINT ; 
 int /*<<< orphan*/  OID_AUTO ; 
 void* SYSCTL_ADD_NODE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,struct ahd_softc*,size_t,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_UINT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (void*) ; 
 int /*<<< orphan*/  SYSCTL_STATIC_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _hw ; 
 int /*<<< orphan*/  ahd_clear_allcounters ; 
 int /*<<< orphan*/  ahd_set_debugcounters ; 
 char** ahd_sysctl_errors_descriptions ; 
 char** ahd_sysctl_errors_elements ; 
 int /*<<< orphan*/ * ahd_sysctl_node_descriptions ; 
 int /*<<< orphan*/ * ahd_sysctl_node_elements ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

void
ahd_sysctl(struct ahd_softc *ahd)
{
	u_int i;

	for (i = 0; i < AHD_SYSCTL_NUMBER; i++)
		sysctl_ctx_init(&ahd->sysctl_ctx[i]);

	ahd->sysctl_tree[AHD_SYSCTL_ROOT] =
	    SYSCTL_ADD_NODE(&ahd->sysctl_ctx[AHD_SYSCTL_ROOT],
			    SYSCTL_STATIC_CHILDREN(_hw), OID_AUTO,
			    device_get_nameunit(ahd->dev_softc), CTLFLAG_RD, 0,
			    ahd_sysctl_node_descriptions[AHD_SYSCTL_ROOT]);
	    SYSCTL_ADD_PROC(&ahd->sysctl_ctx[AHD_SYSCTL_ROOT],
			    SYSCTL_CHILDREN(ahd->sysctl_tree[AHD_SYSCTL_ROOT]),
			    OID_AUTO, "clear", CTLTYPE_UINT | CTLFLAG_RW, ahd,
			    0, ahd_clear_allcounters, "IU",
			    "Clear all counters");

	for (i = AHD_SYSCTL_SUMMARY; i < AHD_SYSCTL_NUMBER; i++)
		ahd->sysctl_tree[i] =
		    SYSCTL_ADD_NODE(&ahd->sysctl_ctx[i],
				    SYSCTL_CHILDREN(ahd->sysctl_tree[AHD_SYSCTL_ROOT]),
				    OID_AUTO, ahd_sysctl_node_elements[i],
				    CTLFLAG_RD, 0,
				    ahd_sysctl_node_descriptions[i]);

	for (i = AHD_ERRORS_CORRECTABLE; i < AHD_ERRORS_NUMBER; i++) {
		SYSCTL_ADD_UINT(&ahd->sysctl_ctx[AHD_SYSCTL_SUMMARY],
				SYSCTL_CHILDREN(ahd->sysctl_tree[AHD_SYSCTL_SUMMARY]),
				OID_AUTO, ahd_sysctl_errors_elements[i],
				CTLFLAG_RD, &ahd->summerr[i], i,
				ahd_sysctl_errors_descriptions[i]);
		SYSCTL_ADD_PROC(&ahd->sysctl_ctx[AHD_SYSCTL_DEBUG],
				SYSCTL_CHILDREN(ahd->sysctl_tree[AHD_SYSCTL_DEBUG]),
				OID_AUTO, ahd_sysctl_errors_elements[i],
				CTLFLAG_RW | CTLTYPE_UINT, ahd, i,
				ahd_set_debugcounters, "IU",
				ahd_sysctl_errors_descriptions[i]);
	}
}