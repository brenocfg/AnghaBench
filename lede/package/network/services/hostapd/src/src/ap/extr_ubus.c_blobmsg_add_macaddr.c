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
typedef  int /*<<< orphan*/  u8 ;
struct blob_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/  const*) ; 
 char* MACSTR ; 
 int /*<<< orphan*/  blobmsg_add_string_buffer (struct blob_buf*) ; 
 char* blobmsg_alloc_string_buffer (struct blob_buf*,char const*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
blobmsg_add_macaddr(struct blob_buf *buf, const char *name, const u8 *addr)
{
	char *s;

	s = blobmsg_alloc_string_buffer(buf, name, 20);
	sprintf(s, MACSTR, MAC2STR(addr));
	blobmsg_add_string_buffer(buf);
}