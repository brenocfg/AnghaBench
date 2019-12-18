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
struct evhttp_connection {int /*<<< orphan*/  bufev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVHTTP_CON_CLOSEDETECT ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  bufferevent_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
evhttp_connection_start_detectclose(struct evhttp_connection *evcon)
{
	evcon->flags |= EVHTTP_CON_CLOSEDETECT;
	bufferevent_enable(evcon->bufev, EV_READ);
}