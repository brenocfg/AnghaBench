#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ fd; struct TYPE_4__* buf; scalar_t__ hdr; int /*<<< orphan*/  multi; int /*<<< orphan*/  curl; } ;
typedef  TYPE_1__ kurl_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  curl_easy_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_multi_remove_handle (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curl_slist_free_all (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int kurl_close(kurl_t *ku)
{
	if (ku == 0) return 0;
	if (ku->fd < 0) {
		curl_multi_remove_handle(ku->multi, ku->curl);
		curl_easy_cleanup(ku->curl);
		curl_multi_cleanup(ku->multi);
		if (ku->hdr) curl_slist_free_all(ku->hdr);
	} else close(ku->fd);
	free(ku->buf);
	free(ku);
	return 0;
}