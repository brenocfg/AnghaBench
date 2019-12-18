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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  emit (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

__attribute__((used)) static void emit_extent(const char *start, const char *end)
{
  char buf[32+1];
  size_t bufmax = sizeof(buf) - 1;
  buf[32] = 0;

  size_t bytes = end - start + 1;

  while (bytes >= bufmax)
  {
    memcpy(buf, start, bufmax);
    emit(buf);
    bytes -= bufmax;
    start += bufmax;
  }
  
  if (bytes == 0)
    return;
  
  memcpy(buf, start, bytes);
  buf[bytes] = 0;
  emit(buf);
}