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
struct strbuf {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* url_decode_internal (char const**,int,char*,struct strbuf*,int) ; 

char *url_decode_parameter_value(const char **query)
{
	struct strbuf out = STRBUF_INIT;
	return url_decode_internal(query, -1, "&", &out, 1);
}