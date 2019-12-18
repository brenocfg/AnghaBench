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
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int H_SIZE ; 
 int NI_NAMEREQD ; 
 char* alloc_string (char*) ; 
 char* gai_strerror (int) ; 
 int getnameinfo (struct sockaddr const*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static char *
reverse_host (const struct sockaddr *a, socklen_t length)
{
  char h[H_SIZE];
  int flags, st;

  flags = NI_NAMEREQD;
  st = getnameinfo (a, length, h, H_SIZE, NULL, 0, flags);
  if (!st)
    return alloc_string (h);
  return alloc_string (gai_strerror (st));
}