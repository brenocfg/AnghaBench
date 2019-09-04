#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  end_proc; } ;
typedef  TYPE_1__ WSClient ;
struct TYPE_7__ {scalar_t__ accesslog; } ;

/* Variables and functions */
 int /*<<< orphan*/  access_log (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int ws_respond (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_2__ wsconfig ; 

__attribute__((used)) static int
http_error (WSClient * client, const char *buffer)
{
  /* do access logging */
  gettimeofday (&client->end_proc, NULL);
  if (wsconfig.accesslog)
    access_log (client, 400);

  return ws_respond (client, buffer, strlen (buffer));
}