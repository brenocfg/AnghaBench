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
struct rchap {int dummy; } ;

/* Variables and functions */
 char* chap_bin2hex (void*,size_t) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  rchap_get_response_bin (struct rchap*,void**,size_t*) ; 

char *
rchap_get_response(struct rchap *rchap)
{
	void *response;
	size_t response_len;
	char *chap_r;

	rchap_get_response_bin(rchap, &response, &response_len);
	chap_r = chap_bin2hex(response, response_len);
	free(response);

	return (chap_r);
}