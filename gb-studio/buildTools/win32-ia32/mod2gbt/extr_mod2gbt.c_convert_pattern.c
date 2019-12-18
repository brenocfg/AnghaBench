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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/ ** info; } ;
typedef  TYPE_1__ _pattern_t ;

/* Variables and functions */
 int /*<<< orphan*/  convert_channel1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_channel2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_channel3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_channel4 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* label_name ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_get_index_from_period (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  out_write_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_write_str (char*,char*) ; 
 int /*<<< orphan*/  unpack_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void convert_pattern(_pattern_t * pattern, u8 number)
{
    out_write_str("const unsigned char ","");
    out_write_str(label_name,label_name);
    out_write_dec(number);
    out_write_str("[] = {\n",":\n");

    int step;
    for(step = 0; step < 64; step ++)
    {
        out_write_str("  ","  DB  ");

        u8 data[4]; //packed data
        u8 samplenum; u16 sampleperiod; u8 effectnum, effectparams; //unpacked data

        u8 note_index;

        //Channel 1
        memcpy(data,pattern->info[step][0],4);
        unpack_info(data,&samplenum,&sampleperiod,&effectnum,&effectparams);
        note_index = mod_get_index_from_period(sampleperiod,number,step,1);

        convert_channel1(number,step,
                         note_index,samplenum,sampleperiod,effectnum,effectparams);
        out_write_str(", ",", ");

        //Channel 2
        memcpy(data,pattern->info[step][1],4);
        unpack_info(data,&samplenum,&sampleperiod,&effectnum,&effectparams);
        note_index = mod_get_index_from_period(sampleperiod,number,step,2);

        convert_channel2(number,step,
                         note_index,samplenum,sampleperiod,effectnum,effectparams);
        out_write_str(", ",", ");

        //Channel 3
        memcpy(data,pattern->info[step][2],4);
        unpack_info(data,&samplenum,&sampleperiod,&effectnum,&effectparams);
        note_index = mod_get_index_from_period(sampleperiod,number,step,3);

        convert_channel3(number,step,
                         note_index,samplenum,sampleperiod,effectnum,effectparams);
        out_write_str(", ",", ");

        //Channel 4
        memcpy(data,pattern->info[step][3],4);
        unpack_info(data,&samplenum,&sampleperiod,&effectnum,&effectparams);
        note_index = mod_get_index_from_period(sampleperiod,number,step,4);

        convert_channel4(number,step,
                         note_index,samplenum,sampleperiod,effectnum,effectparams);

        if(step == 63) out_write_str("\n","\n");
        else out_write_str(",\n","\n");
    }

    out_write_str("};\n\n","\n\n");
}