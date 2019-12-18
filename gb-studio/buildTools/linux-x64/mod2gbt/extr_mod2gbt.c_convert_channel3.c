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
 int volume_mod_to_gb_ch3 (int) ; 

void convert_channel3(u8 pattern_number, u8 step_number, u8 note_index,
                      u8 samplenum, u8 effectnum, u8 effectparams)
{
    u8 result[3] = {0, 0, 0};
    int command_len = 1; // NOP

    if (note_index > (6 * 12 - 1)) // Not valid note -> check if any effect
    {
        if ((effectnum != 0) || (effectparams != 0))
        {
            // Volume or others?
            if (effectnum == 0xC)
            {
                // Volume
                result[0] = BIT(5) | volume_mod_to_gb_ch3(effectparams);
                command_len = 1;
            }
            else
            {
                // Others
                u8 converted_num, converted_params;
                if (effect_mod_to_gb(pattern_number, step_number, 3, effectnum,
                                     effectparams, &converted_num,
                                     &converted_params) == 1)
                {
                    result[0] = BIT(6) | converted_num;
                    result[1] = converted_params;
                    command_len = 2;
                }
                else
                {
                    if (effectnum != 0)
                    {
                        printf("Invalid command at pattern %d, step %d, channel"
                               " 3: %01X%02X\n", pattern_number, step_number,
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
        u8 instrument = (samplenum - 8) & 15; // Only 0-7 implemented

        u8 converted_num, converted_params;
        if (effectnum == 0xC)
        {
            // Note + Volume
            result[0] = BIT(7) | note_index;
            result[1] = (volume_mod_to_gb_ch3(effectparams) << 4) | instrument;
            command_len = 2;
        }
        else
        {
            if (effect_mod_to_gb(pattern_number, step_number, 3, effectnum,
                                 effectparams, &converted_num,
                                 &converted_params) == 1)
            {
                if (converted_num > 7)
                {
                    printf("Invalid command at pattern %d, step %d, channel 3: "
                           "%01X%02X\nOnly 0-7 allowed in this mode.\n",
                           pattern_number, step_number, effectnum,
                           effectparams);
                }
                else
                {
                    // Note + Effect
                    result[0] = BIT(7) | note_index;
                    result[1] = BIT(7) | (converted_num << 4) | instrument;
                    result[2] = converted_params;
                    command_len = 3;
                }
            }
            else // Note + No effect!! -> We need at least volume change!
            {
                printf("Invalid command at pattern %d, step %d, channel 3: "
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