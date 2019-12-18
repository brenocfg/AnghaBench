#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char x; unsigned char y; unsigned char* state; } ;
typedef  TYPE_1__ arcfour_key ;

/* Variables and functions */
 int /*<<< orphan*/  swap_byte (unsigned char*,unsigned char*) ; 

__attribute__((used)) static void arcfour(unsigned char *buffer_ptr, int buffer_len, arcfour_key *key)
{ 
   unsigned char x;
   unsigned char y;
   unsigned char* state;
   unsigned char xorIndex;
   short counter;              
   
   x = key->x;     
   y = key->y;     
   
   state = &key->state[0];         
   for(counter = 0; counter < buffer_len; counter ++)      
   {               
      x = (x + 1) % 256;                      
      y = (state[x] + y) % 256;               
      swap_byte(&state[x], &state[y]);                        
      
      xorIndex = (state[x] + state[y]) % 256;                 
      
      buffer_ptr[counter] ^= state[xorIndex];         
   }               
   key->x = x;     
   key->y = y;
}