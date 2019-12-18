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
typedef  size_t UBYTE ;

/* Variables and functions */
 size_t END ; 
 int /*<<< orphan*/  FREQUENCY ; 
 int /*<<< orphan*/  PLAY ; 
 size_t SILENCE ; 
 int /*<<< orphan*/  delay (int) ; 
 int* frequencies ; 
 size_t* music ; 
 int /*<<< orphan*/  update_value (size_t,int /*<<< orphan*/ ,int) ; 

void play_music(UBYTE mode)
{
  UBYTE i = 0;

  while(music[i] != END) {
    if(music[i] != SILENCE) {
      update_value(mode, FREQUENCY, frequencies[music[i]]);
      update_value(mode, PLAY, 1);
    }
    delay(500);
    i++;
  }
}