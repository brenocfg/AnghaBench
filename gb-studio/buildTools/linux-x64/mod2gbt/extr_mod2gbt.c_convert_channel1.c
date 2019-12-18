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
 int BIT (int) ; 
 int effect_mod_to_gb (int,int,int,int,int,int*,int*) ; 
 int /*<<< orphan*/  out_write_hex (int) ; 
 int /*<<< orphan*/  out_write_str (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int volume_mod_to_gb (int) ; 

void convert_channel1(u8 pattern_number, u8 step_number, u8 note_index,
                      u8 samplenum, u8 effectnum, u8 effectparams)
{
    u8 result[3] = {0, 0, 0};
    int command_len = 1; // NOP

    u8 instrument = samplenum & 3;

    if (note_index > (6 * 12 - 1)) // Not valid note -> check if any effect
    {
        if ((effectnum != 0) || (effectparams != 0))
        {
            // Volume or others?
            if (effectnum == 0xC)
            {
                // Volume
                result[0] = BIT(5) | volume_mod_to_gb(effectparams);
                command_len = 1;
            }
            else
            {
                // Others
                u8 converted_num, converted_params;
                if (effect_mod_to_gb(pattern_number, step_number, 1, effectnum,
                                     effectparams, &converted_num,
                                     &converted_params) == 1)
                {
                    result[0] = BIT(6) | (instrument << 4) | converted_num;
                    result[1] = converted_params;
                    command_len = 2;
                }
                else
                {
                    if (effectnum != 0)
                    {
                        printf("Invalid command at pattern %d, step %d, channel"
                               " 1: %01X%02X\n", pattern_number, step_number,
                               effectnum, effectparams);
                    }

                    // NOP
                    result[0] = 0;
                    command_len = 1;
                }
            }
        }
        else
        {
            // NOP
            result[0] = 0;
            command_len = 1;
        }
    }
    else // New note
    {
        u8 converted_num, converted_params;
        if (effectnum == 0xC)
        {
            // Note + Volume
            result[0] = BIT(7) | note_index;
            result[1] = (instrument << 4) | volume_mod_to_gb(effectparams);
            command_len = 2;
        }
        else
        {
            if (effect_mod_to_gb(pattern_number, step_number, 1, effectnum,
                                 effectparams, &converted_num,
                                 &converted_params) == 1)
            {
                // Note + Effect
                result[0] = BIT(7) | note_index;
                result[1] = BIT(7) | (instrument << 4) | converted_num;
                result[2] = converted_params;
                command_len = 3;
            }
            else // Note + No effect!! -> Bad, we need at least volume change!!
            {
                printf("Invalid command at pattern %d, step %d, channel 1: "
                       "%01X%02X\n", pattern_number, step_number, effectnum,
                       effectparams);

                if (effectnum == 0)
                    printf("Volume must be set when using a note.\n");
            }
        }
    }

    out_write_str("0x");
    out_write_hex(result[0]);

    if (command_len > 1)
    {
        out_write_str(",0x");
        out_write_hex(result[1]);

        if (command_len > 2)
        {
            out_write_str(",0x");
            out_write_hex(result[2]);
        }
    }
}