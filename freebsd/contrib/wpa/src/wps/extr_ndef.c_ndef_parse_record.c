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
typedef  int u32 ;
struct ndef_record {int payload_length; int const* type; int const* id; int const* payload; int total_length; int /*<<< orphan*/  id_length; int /*<<< orphan*/  type_length; } ;

/* Variables and functions */
 int const FLAG_ID_LENGTH_PRESENT ; 
 int const FLAG_SHORT_RECORD ; 
 int WPA_GET_BE32 (int const*) ; 

__attribute__((used)) static int ndef_parse_record(const u8 *data, u32 size,
			     struct ndef_record *record)
{
	const u8 *pos = data + 1;

	if (size < 2)
		return -1;
	record->type_length = *pos++;
	if (data[0] & FLAG_SHORT_RECORD) {
		if (size < 3)
			return -1;
		record->payload_length = *pos++;
	} else {
		u32 len;

		if (size < 6)
			return -1;
		len = WPA_GET_BE32(pos);
		if (len > size - 6 || len > 20000)
			return -1;
		record->payload_length = len;
		pos += sizeof(u32);
	}

	if (data[0] & FLAG_ID_LENGTH_PRESENT) {
		if ((int) size < pos - data + 1)
			return -1;
		record->id_length = *pos++;
	} else
		record->id_length = 0;

	record->type = record->type_length == 0 ? NULL : pos;
	pos += record->type_length;

	record->id = record->id_length == 0 ? NULL : pos;
	pos += record->id_length;

	record->payload = record->payload_length == 0 ? NULL : pos;
	pos += record->payload_length;

	record->total_length = pos - data;
	if (record->total_length > size ||
	    record->total_length < record->payload_length)
		return -1;
	return 0;
}