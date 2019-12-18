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
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 scalar_t__ sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_read_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 

__attribute__((used)) static int
read_fixed(RES* ssl, sldns_buffer* buf, const char* str)
{
	if(!ssl_read_buf(ssl, buf)) return 0;
	return (strcmp((char*)sldns_buffer_begin(buf), str) == 0);
}