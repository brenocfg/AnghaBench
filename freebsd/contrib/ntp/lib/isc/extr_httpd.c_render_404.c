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
typedef  int /*<<< orphan*/  isc_result_t ;
typedef  int /*<<< orphan*/  isc_httpdfree_t ;
typedef  int /*<<< orphan*/  isc_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  UNUSED (void*) ; 
 int /*<<< orphan*/  isc_buffer_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_buffer_reinit (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static isc_result_t
render_404(const char *url, const char *querystring,
	   void *arg,
	   unsigned int *retcode, const char **retmsg,
	   const char **mimetype, isc_buffer_t *b,
	   isc_httpdfree_t **freecb, void **freecb_args)
{
	static char msg[] = "No such URL.";

	UNUSED(url);
	UNUSED(querystring);
	UNUSED(arg);

	*retcode = 404;
	*retmsg = "No such URL";
	*mimetype = "text/plain";
	isc_buffer_reinit(b, msg, strlen(msg));
	isc_buffer_add(b, strlen(msg));
	*freecb = NULL;
	*freecb_args = NULL;

	return (ISC_R_SUCCESS);
}