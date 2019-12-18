#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  tim ;
struct tm {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tv_sec; } ;
struct node_info {int chan; int max; struct node_info* next; int /*<<< orphan*/  wep; int /*<<< orphan*/  mac; TYPE_1__ seen; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,char*,int,char*,int) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 char* mac2str (int /*<<< orphan*/ ) ; 
 struct node_info* nodes ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* ssid2str (struct node_info*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 char* wep2str (int /*<<< orphan*/ ) ; 

void save_state() {
	FILE* f;
	struct node_info* node = nodes;

	f = fopen("stumbler.log", "w");
	if (!f) {
		perror("fopen()");
		exit(1);
	}	

	while (node) {
		struct tm* t;
		char tim[16];

		t = localtime( (time_t*) &node->seen.tv_sec);
		if (!t) {
			perror("localtime()");
			exit(1);
		}
		tim[0] = 0;
		strftime(tim, sizeof(tim), "%H:%M:%S", t);
	
		fprintf(f, "%s %s %s %2d %s 0x%.2x\n", tim,
			mac2str(node->mac), wep2str(node->wep),
			node->chan, ssid2str(node), node->max);

		node = node->next;	
	}

	fclose(f);
}