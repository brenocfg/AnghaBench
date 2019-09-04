#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* referer; void* agent; void* ws_sock_ver; void* ws_key; void* ws_protocol; void* connection; void* upgrade; void* origin; void* host; } ;
typedef  TYPE_1__ WSHeaders ;

/* Variables and functions */
 scalar_t__ strcasecmp (char*,char*) ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static void
ws_set_header_key_value (WSHeaders * headers, char *key, char *value)
{
  if (strcasecmp ("Host", key) == 0)
    headers->host = xstrdup (value);
  else if (strcasecmp ("Origin", key) == 0)
    headers->origin = xstrdup (value);
  else if (strcasecmp ("Upgrade", key) == 0)
    headers->upgrade = xstrdup (value);
  else if (strcasecmp ("Connection", key) == 0)
    headers->connection = xstrdup (value);
  else if (strcasecmp ("Sec-WebSocket-Protocol", key) == 0)
    headers->ws_protocol = xstrdup (value);
  else if (strcasecmp ("Sec-WebSocket-Key", key) == 0)
    headers->ws_key = xstrdup (value);
  else if (strcasecmp ("Sec-WebSocket-Version", key) == 0)
    headers->ws_sock_ver = xstrdup (value);
  else if (strcasecmp ("User-Agent", key) == 0)
    headers->agent = xstrdup (value);
  else if (strcasecmp ("Referer", key) == 0)
    headers->referer = xstrdup (value);
}