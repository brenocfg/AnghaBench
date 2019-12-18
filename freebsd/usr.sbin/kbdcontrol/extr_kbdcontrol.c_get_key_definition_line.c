#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* key; } ;
typedef  TYPE_2__ keymap_t ;
struct TYPE_4__ {int spcl; int* map; void* flgs; } ;

/* Variables and functions */
 void* NUM_KEYS ; 
 int NUM_STATES ; 
 int SPECIAL ; 
 int /*<<< orphan*/  TFLAG ; 
 int get_entry () ; 
 void* number ; 
 int /*<<< orphan*/  token ; 
 int /*<<< orphan*/  yylex () ; 

__attribute__((used)) static int
get_key_definition_line(keymap_t *map)
{
	int i, def, scancode;

	/* check scancode number */
	if (number < 0 || number >= NUM_KEYS)
		return -1;
	scancode = number;

	/* get key definitions */
	map->key[scancode].spcl = 0;
	for (i=0; i<NUM_STATES; i++) {
		if ((def = get_entry()) == -1)
			return -1;
		if (def & SPECIAL)
			map->key[scancode].spcl |= (0x80 >> i);
		map->key[scancode].map[i] = def & ~SPECIAL;
	}
	/* get lock state key def */
	if ((token = yylex()) != TFLAG)
		return -1;
	map->key[scancode].flgs = number;
	token = yylex();
	return (scancode + 1);
}