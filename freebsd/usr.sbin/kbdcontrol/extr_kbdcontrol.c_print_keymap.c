#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int n_keys; int /*<<< orphan*/ * acc; int /*<<< orphan*/ * key; } ;
typedef  TYPE_1__ keymap_t ;
typedef  TYPE_1__ accentmap_t ;
typedef  int /*<<< orphan*/  accentmap ;

/* Variables and functions */
 int /*<<< orphan*/  GIO_DEADKEYMAP ; 
 int /*<<< orphan*/  GIO_KEYMAP ; 
 int NUM_DEADKEYS ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_accent_definition_line (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_key_definition_line (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void
print_keymap(void)
{
	keymap_t keymap;
	accentmap_t accentmap;
	int i;

	if (ioctl(0, GIO_KEYMAP, &keymap) < 0)
		err(1, "getting keymap");
	if (ioctl(0, GIO_DEADKEYMAP, &accentmap) < 0)
		memset(&accentmap, 0, sizeof(accentmap));
    	printf(
"#                                                         alt\n"
"# scan                       cntrl          alt    alt   cntrl lock\n"
"# code  base   shift  cntrl  shift  alt    shift  cntrl  shift state\n"
"# ------------------------------------------------------------------\n"
    	);
	for (i=0; i<keymap.n_keys; i++)
		print_key_definition_line(stdout, i, &keymap.key[i]);

	printf("\n");
	for (i = 0; i < NUM_DEADKEYS; i++)
		print_accent_definition_line(stdout, i, &accentmap.acc[i]);

}