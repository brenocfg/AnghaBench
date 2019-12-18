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
typedef  int u8 ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int,int,int) ; 
 int speed_mod_to_gb (int) ; 

int effect_mod_to_gb(u8 pattern_number, u8 step_number, u8 channel,
                     u8 effectnum, u8 effectparams, u8 *converted_num,
                     u8 *converted_params)
{
    switch (effectnum)
    {
        case 0x0: // Arpeggio
        {
            *converted_num = 1;
            *converted_params = effectparams;
            return 1;
        }
        case 0xB: // Jump
        {
            *converted_num = 8;
            *converted_params = effectparams;
            return 1;
        }
        case 0xC: // Volume -> Not handled here
        {
            printf("Strange error at pattern %d, step %d, channel %d: "
                   "%01X%02X\n", pattern_number, step_number, channel,
                   effectnum, effectparams);
            return 0;
        }
        case 0xD: // Break + Set step
        {
            *converted_num = 9; // Effect value is BCD, convert to integer
            *converted_params = (((effectparams & 0xF0) >> 4) * 10)
                              +   (effectparams & 0x0F);
            //*converted_params = effectparams; // ... or not?
            return 1;
        }
        case 0xE:
        {
            if ((effectparams & 0xF0) == 0x80) // Pan
            {
                u8 left = 0;
                u8 right = 0;

                switch (effectparams & 0xF)
                {
                    case 0: case 1: case 2: case 3:
                        left = 1;
                        break;

                    default:
                    case 4: case 5: case 6: case 7:
                    case 8: case 9: case 10: case 11:
                        left = 1;
                        right = 1;
                        break;

                    case 12: case 13: case 14: case 15:
                        right = 1;
                        break;
                }
                *converted_num = 0;
                *converted_params = (left << (3 + channel))
                                  | (right << (channel - 1)); // Channel 1-4
                return 1;
            }
            if ((effectparams & 0xF0) == 0xC0) // Cut note
            {
                *converted_num = 2;
                *converted_params = (effectparams & 0xF);
                return 1;
            }
            else // Error
            {
                printf("Unsupported effect at pattern %d, step %d, channel %d: "
                       "%01X%02X\n", pattern_number, step_number, channel,
                       effectnum, effectparams);
                return 0;
            }
            break;
        }
        case 0xF: // Speed
        {
            if (effectparams > 0x1F) // Nothing
            {
                printf("Unsupported BPM speed effect at pattern %d, step %d, "
                       "channel %d: %01X%02X\n", pattern_number, step_number,
                       channel, effectnum, effectparams);
                return 0;
            }
            else // Speed
            {
                *converted_num = 10;
                *converted_params = speed_mod_to_gb(effectparams);
                return 1;
            }
            break;
        }
        default: // Nothing
        {
            printf("Unsupported effect at pattern %d, step %d, channel %d: "
                   "%01X%02X\n", pattern_number, step_number, channel,
                   effectnum, effectparams);
            return 0;
        }
    }
    return 0;
}