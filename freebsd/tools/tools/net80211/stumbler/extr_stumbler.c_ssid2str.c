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
struct node_info {char* ssid; scalar_t__ ap; } ;
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

char* ssid2str(struct node_info* node) {
	static char res[24];

	memset(res, ' ', sizeof(res));
	res[0] = '[';
	strcpy(&res[sizeof(res)-2], "]");

	if (node->ap) {
		int left = sizeof(res) - 3;

		if (strlen(node->ssid) < left)
			left = strlen(node->ssid);
		memcpy(&res[1], node->ssid, left);
	}	
	else {
		memcpy(&res[1], "<client>", 8);
	}
	return res;
}