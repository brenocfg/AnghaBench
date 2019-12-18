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
typedef  void* u_int8_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/  PUTLONG (int,int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 int latlon2ul (char const**,int*) ; 
 void* precsize_aton (char const**) ; 
 int strlen (char const*) ; 

int
loc_aton(const char *ascii, u_char *binary)
{
	const char *cp, *maxcp;
	u_char *bcp;

	u_int32_t latit = 0, longit = 0, alt = 0;
	u_int32_t lltemp1 = 0, lltemp2 = 0;
	int altmeters = 0, altfrac = 0, altsign = 1;
	u_int8_t hp = 0x16;	/*%< default = 1e6 cm = 10000.00m = 10km */
	u_int8_t vp = 0x13;	/*%< default = 1e3 cm = 10.00m */
	u_int8_t siz = 0x12;	/*%< default = 1e2 cm = 1.00m */
	int which1 = 0, which2 = 0;

	cp = ascii;
	maxcp = cp + strlen(ascii);

	lltemp1 = latlon2ul(&cp, &which1);

	lltemp2 = latlon2ul(&cp, &which2);

	switch (which1 + which2) {
	case 3:			/*%< 1 + 2, the only valid combination */
		if ((which1 == 1) && (which2 == 2)) { /*%< normal case */
			latit = lltemp1;
			longit = lltemp2;
		} else if ((which1 == 2) && (which2 == 1)) { /*%< reversed */
			longit = lltemp1;
			latit = lltemp2;
		} else {	/*%< some kind of brokenness */
			return (0);
		}
		break;
	default:		/*%< we didn't get one of each */
		return (0);
	}

	/* altitude */
	if (*cp == '-') {
		altsign = -1;
		cp++;
	}

	if (*cp == '+')
		cp++;

	while (isdigit((unsigned char)*cp))
		altmeters = altmeters * 10 + (*cp++ - '0');

	if (*cp == '.') {		/*%< decimal meters */
		cp++;
		if (isdigit((unsigned char)*cp)) {
			altfrac = (*cp++ - '0') * 10;
			if (isdigit((unsigned char)*cp)) {
				altfrac += (*cp++ - '0');
			}
		}
	}

	alt = (10000000 + (altsign * (altmeters * 100 + altfrac)));

	while (!isspace((unsigned char)*cp) && (cp < maxcp)) /*%< if trailing garbage or m */
		cp++;

	while (isspace((unsigned char)*cp) && (cp < maxcp))
		cp++;

	if (cp >= maxcp)
		goto defaults;

	siz = precsize_aton(&cp);

	while (!isspace((unsigned char)*cp) && (cp < maxcp))	/*%< if trailing garbage or m */
		cp++;

	while (isspace((unsigned char)*cp) && (cp < maxcp))
		cp++;

	if (cp >= maxcp)
		goto defaults;

	hp = precsize_aton(&cp);

	while (!isspace((unsigned char)*cp) && (cp < maxcp))	/*%< if trailing garbage or m */
		cp++;

	while (isspace((unsigned char)*cp) && (cp < maxcp))
		cp++;

	if (cp >= maxcp)
		goto defaults;

	vp = precsize_aton(&cp);

 defaults:

	bcp = binary;
	*bcp++ = (u_int8_t) 0;	/*%< version byte */
	*bcp++ = siz;
	*bcp++ = hp;
	*bcp++ = vp;
	PUTLONG(latit,bcp);
	PUTLONG(longit,bcp);
	PUTLONG(alt,bcp);

	return (16);		/*%< size of RR in octets */
}