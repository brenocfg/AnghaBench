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
typedef  enum evhttp_cmd_type { ____Placeholder_evhttp_cmd_type } evhttp_cmd_type ;

/* Variables and functions */
#define  EVHTTP_REQ_CONNECT 136 
#define  EVHTTP_REQ_DELETE 135 
#define  EVHTTP_REQ_GET 134 
#define  EVHTTP_REQ_HEAD 133 
#define  EVHTTP_REQ_OPTIONS 132 
#define  EVHTTP_REQ_PATCH 131 
#define  EVHTTP_REQ_POST 130 
#define  EVHTTP_REQ_PUT 129 
#define  EVHTTP_REQ_TRACE 128 

__attribute__((used)) static int
evhttp_method_may_have_body(enum evhttp_cmd_type type)
{
	switch (type) {
	case EVHTTP_REQ_POST:
	case EVHTTP_REQ_PUT:
	case EVHTTP_REQ_PATCH:
		return 1;
	case EVHTTP_REQ_TRACE:
		return 0;
	/* XXX May any of the below methods have a body? */
	case EVHTTP_REQ_GET:
	case EVHTTP_REQ_HEAD:
	case EVHTTP_REQ_DELETE:
	case EVHTTP_REQ_OPTIONS:
	case EVHTTP_REQ_CONNECT:
		return 0;
	default:
		return 0;
	}
}