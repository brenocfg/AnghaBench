#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct http_object_request {TYPE_1__* slot; int /*<<< orphan*/  http_code; int /*<<< orphan*/  curl_result; } ;
struct TYPE_2__ {int /*<<< orphan*/  http_code; int /*<<< orphan*/  curl_result; } ;

/* Variables and functions */

void process_http_object_request(struct http_object_request *freq)
{
	if (freq->slot == NULL)
		return;
	freq->curl_result = freq->slot->curl_result;
	freq->http_code = freq->slot->http_code;
	freq->slot = NULL;
}