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
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;
struct http_object_request {TYPE_1__ tmpfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_http_object_request (struct http_object_request*) ; 
 int /*<<< orphan*/  unlink_or_warn (int /*<<< orphan*/ ) ; 

void abort_http_object_request(struct http_object_request *freq)
{
	unlink_or_warn(freq->tmpfile.buf);

	release_http_object_request(freq);
}