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
struct evhttp_connection {int state; } ;

/* Variables and functions */
#define  EVCON_CONNECTING 135 
#define  EVCON_DISCONNECTED 134 
#define  EVCON_IDLE 133 
#define  EVCON_READING_BODY 132 
#define  EVCON_READING_FIRSTLINE 131 
#define  EVCON_READING_HEADERS 130 
#define  EVCON_READING_TRAILER 129 
#define  EVCON_WRITING 128 

__attribute__((used)) static int
evhttp_connected(struct evhttp_connection *evcon)
{
	switch (evcon->state) {
	case EVCON_DISCONNECTED:
	case EVCON_CONNECTING:
		return (0);
	case EVCON_IDLE:
	case EVCON_READING_FIRSTLINE:
	case EVCON_READING_HEADERS:
	case EVCON_READING_BODY:
	case EVCON_READING_TRAILER:
	case EVCON_WRITING:
	default:
		return (1);
	}
}