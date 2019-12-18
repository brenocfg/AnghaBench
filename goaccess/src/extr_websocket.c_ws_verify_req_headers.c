#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ws_sock_ver; int /*<<< orphan*/  ws_key; int /*<<< orphan*/  connection; int /*<<< orphan*/  origin; int /*<<< orphan*/  path; int /*<<< orphan*/  protocol; int /*<<< orphan*/  method; int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ WSHeaders ;
struct TYPE_5__ {scalar_t__ origin; } ;

/* Variables and functions */
 scalar_t__ strcasecmp (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__ wsconfig ; 

__attribute__((used)) static int
ws_verify_req_headers (WSHeaders * headers)
{
  if (!headers->host)
    return 1;
  if (!headers->method)
    return 1;
  if (!headers->protocol)
    return 1;
  if (!headers->path)
    return 1;
  if (wsconfig.origin && !headers->origin)
    return 1;
  if (wsconfig.origin && strcasecmp (wsconfig.origin, headers->origin) != 0)
    return 1;
  if (!headers->connection)
    return 1;
  if (!headers->ws_key)
    return 1;
  if (!headers->ws_sock_ver)
    return 1;
  return 0;
}