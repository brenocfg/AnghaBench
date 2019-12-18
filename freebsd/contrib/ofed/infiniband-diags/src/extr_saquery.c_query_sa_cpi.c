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
struct sa_query_result {scalar_t__ status; int /*<<< orphan*/  p_result_madw; } ;
struct sa_handle {int dummy; } ;
struct query_params {int /*<<< orphan*/  cpi; } ;
typedef  int /*<<< orphan*/  ib_class_port_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_PORT_INFO ; 
 int EIO ; 
 int /*<<< orphan*/  IB_MAD_METHOD_GET ; 
 scalar_t__ IB_SA_MAD_STATUS_SUCCESS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ibd_sakey ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sa_free_result_mad (struct sa_query_result*) ; 
 int /*<<< orphan*/ * sa_get_query_rec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sa_query (struct sa_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sa_query_result*) ; 
 int /*<<< orphan*/  sa_report_err (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int) ; 

__attribute__((used)) static int query_sa_cpi(struct sa_handle *h, struct query_params *query_params)
{
	ib_class_port_info_t *cpi;
	struct sa_query_result result;
	int ret = sa_query(h, IB_MAD_METHOD_GET, CLASS_PORT_INFO, 0, 0,
		       ibd_sakey, NULL, 0, &result);
	if (ret) {
		fprintf(stderr, "Query SA failed: %s\n", strerror(ret));
		return ret;
	}

	if (result.status != IB_SA_MAD_STATUS_SUCCESS) {
		sa_report_err(result.status);
		ret = EIO;
		goto Exit;
	}
	cpi = sa_get_query_rec(result.p_result_madw, 0);
	memcpy(&query_params->cpi, cpi, sizeof(query_params->cpi));
Exit:
	sa_free_result_mad(&result);
	return (0);
}