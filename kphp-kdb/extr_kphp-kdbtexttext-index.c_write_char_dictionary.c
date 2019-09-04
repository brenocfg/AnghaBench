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
struct char_dictionary {int* code_len; int /*<<< orphan*/  freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  initcrc () ; 
 int /*<<< orphan*/  write_freq_int_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writecrc () ; 
 int /*<<< orphan*/  writeout (int*,int) ; 

void write_char_dictionary (struct char_dictionary *Dict) {
  static int dict_size = 256;
  initcrc ();
  writeout (&dict_size, 4);
  writeout (Dict->code_len, 256);
  writecrc ();
  write_freq_int_array (Dict->freq);
  writecrc ();
}