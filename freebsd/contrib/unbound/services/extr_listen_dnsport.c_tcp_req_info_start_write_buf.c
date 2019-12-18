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
typedef  int /*<<< orphan*/  uint8_t ;
struct tcp_req_info {TYPE_1__* cp; } ;
struct TYPE_2__ {scalar_t__ tcp_is_reading; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
tcp_req_info_start_write_buf(struct tcp_req_info* req, uint8_t* buf,
	size_t len)
{
	sldns_buffer_clear(req->cp->buffer);
	sldns_buffer_write(req->cp->buffer, buf, len);
	sldns_buffer_flip(req->cp->buffer);

	req->cp->tcp_is_reading = 0; /* we are now writing */
}