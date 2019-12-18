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
struct memory_packet_config {scalar_t__ fixed_p; int /*<<< orphan*/  size; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_memory_packet_size (struct memory_packet_config*) ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
show_memory_packet_size (struct memory_packet_config *config)
{
  printf_filtered ("The %s is %ld. ", config->name, config->size);
  if (config->fixed_p)
    printf_filtered ("Packets are fixed at %ld bytes.\n",
		     get_memory_packet_size (config));
  else
    printf_filtered ("Packets are limited to %ld bytes.\n",
		     get_memory_packet_size (config));
}