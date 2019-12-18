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
struct packet_config {int support; int detect; int /*<<< orphan*/  title; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  AUTO_BOOLEAN_AUTO 133 
#define  AUTO_BOOLEAN_FALSE 132 
#define  AUTO_BOOLEAN_TRUE 131 
#define  PACKET_DISABLE 130 
#define  PACKET_ENABLE 129 
#define  PACKET_SUPPORT_UNKNOWN 128 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
show_packet_config_cmd (struct packet_config *config)
{
  char *support = "internal-error";
  switch (config->support)
    {
    case PACKET_ENABLE:
      support = "enabled";
      break;
    case PACKET_DISABLE:
      support = "disabled";
      break;
    case PACKET_SUPPORT_UNKNOWN:
      support = "unknown";
      break;
    }
  switch (config->detect)
    {
    case AUTO_BOOLEAN_AUTO:
      printf_filtered ("Support for remote protocol `%s' (%s) packet is auto-detected, currently %s.\n",
		       config->name, config->title, support);
      break;
    case AUTO_BOOLEAN_TRUE:
    case AUTO_BOOLEAN_FALSE:
      printf_filtered ("Support for remote protocol `%s' (%s) packet is currently %s.\n",
		       config->name, config->title, support);
      break;
    }
}