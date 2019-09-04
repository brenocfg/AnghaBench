#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpc_in_data {TYPE_2__* rpc; TYPE_1__* slot; } ;
struct TYPE_4__ {int any_written; int /*<<< orphan*/  in; } ;
struct TYPE_3__ {int /*<<< orphan*/  curl; } ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  CURLINFO_RESPONSE_CODE ; 
 scalar_t__ curl_easy_getinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,long*) ; 
 int /*<<< orphan*/  write_or_die (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static size_t rpc_in(char *ptr, size_t eltsize,
		size_t nmemb, void *buffer_)
{
	size_t size = eltsize * nmemb;
	struct rpc_in_data *data = buffer_;
	long response_code;

	if (curl_easy_getinfo(data->slot->curl, CURLINFO_RESPONSE_CODE,
			      &response_code) != CURLE_OK)
		return size;
	if (response_code >= 300)
		return size;
	if (size)
		data->rpc->any_written = 1;
	write_or_die(data->rpc->in, ptr, size);
	return size;
}