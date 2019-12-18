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
struct packet_config {int detect; int /*<<< orphan*/  support; } ;

/* Variables and functions */
#define  AUTO_BOOLEAN_AUTO 130 
#define  AUTO_BOOLEAN_FALSE 129 
#define  AUTO_BOOLEAN_TRUE 128 
 int /*<<< orphan*/  PACKET_DISABLE ; 
 int /*<<< orphan*/  PACKET_ENABLE ; 
 int /*<<< orphan*/  PACKET_SUPPORT_UNKNOWN ; 

__attribute__((used)) static void
update_packet_config (struct packet_config *config)
{
  switch (config->detect)
    {
    case AUTO_BOOLEAN_TRUE:
      config->support = PACKET_ENABLE;
      break;
    case AUTO_BOOLEAN_FALSE:
      config->support = PACKET_DISABLE;
      break;
    case AUTO_BOOLEAN_AUTO:
      config->support = PACKET_SUPPORT_UNKNOWN;
      break;
    }
}