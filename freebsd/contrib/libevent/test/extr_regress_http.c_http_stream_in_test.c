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

/* Variables and functions */
 char* BASIC_REQUEST_BODY ; 
 int /*<<< orphan*/  http_stream_in_test_ (void*,char*,int,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
http_stream_in_test(void *arg)
{
	http_stream_in_test_(arg, "/chunked", 13 + 18 + 8,
	    "This is funnybut not hilarious.bwv 1052");

	http_stream_in_test_(arg, "/test", strlen(BASIC_REQUEST_BODY),
	    BASIC_REQUEST_BODY);
}