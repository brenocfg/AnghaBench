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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ loc_cm_print (char**,size_t*,scalar_t__,scalar_t__) ; 
 int sldns_read_uint32 (scalar_t__*) ; 
 scalar_t__ sldns_str_print (char**,size_t*,char*,...) ; 
 int sldns_wire2str_hex_scan (scalar_t__**,size_t*,char**,size_t*) ; 

int sldns_wire2str_loc_scan(uint8_t** d, size_t* dl, char** str, size_t* sl)
{
	/* we could do checking (ie degrees < 90 etc)? */
	uint8_t version;
	uint8_t size;
	uint8_t horizontal_precision;
	uint8_t vertical_precision;
	uint32_t longitude;
	uint32_t latitude;
	uint32_t altitude;
	char northerness;
	char easterness;
	uint32_t h;
	uint32_t m;
	double s;
	uint32_t equator = (uint32_t)1 << 31; /* 2**31 */
	int w = 0;

	if(*dl < 16) return -1;
	version = (*d)[0];
	if(version != 0)
		return sldns_wire2str_hex_scan(d, dl, str, sl);
	size = (*d)[1];
	horizontal_precision = (*d)[2];
	vertical_precision = (*d)[3];

	latitude = sldns_read_uint32((*d)+4);
	longitude = sldns_read_uint32((*d)+8);
	altitude = sldns_read_uint32((*d)+12);

	if (latitude > equator) {
		northerness = 'N';
		latitude = latitude - equator;
	} else {
		northerness = 'S';
		latitude = equator - latitude;
	}
	h = latitude / (1000 * 60 * 60);
	latitude = latitude % (1000 * 60 * 60);
	m = latitude / (1000 * 60);
	latitude = latitude % (1000 * 60);
	s = (double) latitude / 1000.0;
	w += sldns_str_print(str, sl, "%02u %02u %06.3f %c ",
		h, m, s, northerness);

	if (longitude > equator) {
		easterness = 'E';
		longitude = longitude - equator;
	} else {
		easterness = 'W';
		longitude = equator - longitude;
	}
	h = longitude / (1000 * 60 * 60);
	longitude = longitude % (1000 * 60 * 60);
	m = longitude / (1000 * 60);
	longitude = longitude % (1000 * 60);
	s = (double) longitude / (1000.0);
	w += sldns_str_print(str, sl, "%02u %02u %06.3f %c ",
		h, m, s, easterness);

	s = ((double) altitude) / 100;
	s -= 100000;

	if(altitude%100 != 0)
		w += sldns_str_print(str, sl, "%.2f", s);
	else
		w += sldns_str_print(str, sl, "%.0f", s);

	w += sldns_str_print(str, sl, "m ");

	w += loc_cm_print(str, sl, (size & 0xf0) >> 4, size & 0x0f);
	w += sldns_str_print(str, sl, "m ");

	w += loc_cm_print(str, sl, (horizontal_precision & 0xf0) >> 4,
		horizontal_precision & 0x0f);
	w += sldns_str_print(str, sl, "m ");

	w += loc_cm_print(str, sl, (vertical_precision & 0xf0) >> 4,
		vertical_precision & 0x0f);
	w += sldns_str_print(str, sl, "m");

	(*d)+=16;
	(*dl)-=16;
	return w;
}