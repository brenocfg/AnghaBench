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
struct http_pack_request {struct http_pack_request* url; int /*<<< orphan*/  tmpfile; int /*<<< orphan*/ * slot; int /*<<< orphan*/ * packfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct http_pack_request*) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

void release_http_pack_request(struct http_pack_request *preq)
{
	if (preq->packfile != NULL) {
		fclose(preq->packfile);
		preq->packfile = NULL;
	}
	preq->slot = NULL;
	strbuf_release(&preq->tmpfile);
	free(preq->url);
	free(preq);
}