#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gss_buffer_t ;
typedef  TYPE_2__* gss_OID ;
struct TYPE_8__ {size_t length; scalar_t__ elements; } ;
struct TYPE_7__ {void* value; scalar_t__ length; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 TYPE_2__* GSS_C_NULL_OID ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  _gss_buffer_zero (TYPE_1__*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

OM_uint32
gss_oid_to_str(OM_uint32 *minor_status, gss_OID oid, gss_buffer_t oid_str)
{
	char		numstr[128];
	unsigned long	number;
	int		numshift;
	size_t		string_length;
	size_t		i;
	unsigned char	*cp;
	char		*bp;

	*minor_status = 0;
	_gss_buffer_zero(oid_str);

	if (oid == GSS_C_NULL_OID)
		return (GSS_S_FAILURE);

	/* Decoded according to krb5/gssapi_krb5.c */

	/* First determine the size of the string */
	string_length = 0;
	number = 0;
	numshift = 0;
	cp = (unsigned char *) oid->elements;
	number = (unsigned long) cp[0];
	sprintf(numstr, "%ld ", number/40);
	string_length += strlen(numstr);
	sprintf(numstr, "%ld ", number%40);
	string_length += strlen(numstr);
	for (i=1; i<oid->length; i++) {
		if ( (size_t) (numshift+7) < (sizeof(unsigned long)*8)) {
			number = (number << 7) | (cp[i] & 0x7f);
			numshift += 7;
		}
		else {
			*minor_status = 0;
			return(GSS_S_FAILURE);
		}
		if ((cp[i] & 0x80) == 0) {
			sprintf(numstr, "%ld ", number);
			string_length += strlen(numstr);
			number = 0;
			numshift = 0;
		}
	}
	/*
	 * If we get here, we've calculated the length of "n n n ... n ".
	 * Add 4 here for "{ " and "}\0".
	 */
	string_length += 4;
	if ((bp = (char *) malloc(string_length))) {
		strcpy(bp, "{ ");
		number = (unsigned long) cp[0];
		sprintf(numstr, "%ld ", number/40);
		strcat(bp, numstr);
		sprintf(numstr, "%ld ", number%40);
		strcat(bp, numstr);
		number = 0;
		cp = (unsigned char *) oid->elements;
		for (i=1; i<oid->length; i++) {
			number = (number << 7) | (cp[i] & 0x7f);
			if ((cp[i] & 0x80) == 0) {
				sprintf(numstr, "%ld ", number);
				strcat(bp, numstr);
				number = 0;
			}
		}
		strcat(bp, "}");
		oid_str->length = strlen(bp)+1;
		oid_str->value = (void *) bp;
		*minor_status = 0;
		return(GSS_S_COMPLETE);
	}
	*minor_status = ENOMEM;
	return(GSS_S_FAILURE);
}