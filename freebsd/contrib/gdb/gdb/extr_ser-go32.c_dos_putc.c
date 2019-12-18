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
struct dos_ttystate {int count; int* cbuf; int first; } ;

/* Variables and functions */
 int CBSIZE ; 

__attribute__((used)) static int
dos_putc (int c, struct dos_ttystate *port)
{
  if (port->count >= CBSIZE - 1)
    return -1;
  port->cbuf[(port->first + port->count) & (CBSIZE - 1)] = c;
  port->count++;
  return 0;
}