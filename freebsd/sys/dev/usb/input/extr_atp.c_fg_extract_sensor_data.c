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
typedef  int u_int ;
typedef  int int8_t ;
typedef  enum fountain_geyser_trackpad_type { ____Placeholder_fountain_geyser_trackpad_type } fountain_geyser_trackpad_type ;
typedef  int /*<<< orphan*/  atp_axis ;

/* Variables and functions */
#define  FG_TRACKPAD_TYPE_GEYSER1 131 
#define  FG_TRACKPAD_TYPE_GEYSER2 130 
#define  FG_TRACKPAD_TYPE_GEYSER3 129 
#define  FG_TRACKPAD_TYPE_GEYSER4 128 
 int /*<<< orphan*/  X ; 
 int /*<<< orphan*/  Y ; 

__attribute__((used)) static void
fg_extract_sensor_data(const int8_t *sensor_data, u_int num, atp_axis axis,
    int	*arr, enum fountain_geyser_trackpad_type prot)
{
	u_int i;
	u_int di;   /* index into sensor data */

	switch (prot) {
	case FG_TRACKPAD_TYPE_GEYSER1:
		/*
		 * For Geyser 1, the sensors are laid out in pairs
		 * every 5 bytes.
		 */
		for (i = 0, di = (axis == Y) ? 1 : 2; i < 8; di += 5, i++) {
			arr[i] = sensor_data[di];
			arr[i+8] = sensor_data[di+2];
			if ((axis == X) && (num > 16))
				arr[i+16] = sensor_data[di+40];
		}

		break;
	case FG_TRACKPAD_TYPE_GEYSER2:
		for (i = 0, di = (axis == Y) ? 1 : 19; i < num; /* empty */ ) {
			arr[i++] = sensor_data[di++];
			arr[i++] = sensor_data[di++];
			di++;
		}
		break;
	case FG_TRACKPAD_TYPE_GEYSER3:
	case FG_TRACKPAD_TYPE_GEYSER4:
		for (i = 0, di = (axis == Y) ? 2 : 20; i < num; /* empty */ ) {
			arr[i++] = sensor_data[di++];
			arr[i++] = sensor_data[di++];
			di++;
		}
		break;
	default:
		break;
	}
}