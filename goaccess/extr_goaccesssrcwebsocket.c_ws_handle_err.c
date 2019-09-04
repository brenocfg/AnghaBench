#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WSStatus ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ WSClient ;

/* Variables and functions */
 int ws_error (TYPE_1__*,unsigned short,char const*) ; 

__attribute__((used)) static int
ws_handle_err (WSClient * client, unsigned short code, WSStatus status,
               const char *m)
{
  client->status = status;
  return ws_error (client, code, m);
}