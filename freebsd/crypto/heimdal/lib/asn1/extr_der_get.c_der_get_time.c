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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int ASN1_BAD_LENGTH ; 
 int ENOMEM ; 
 int /*<<< orphan*/  free (char*) ; 
 int generalizedtime2time (char*,int /*<<< orphan*/ *) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,unsigned char const*,size_t) ; 

__attribute__((used)) static int
der_get_time (const unsigned char *p, size_t len,
	      time_t *data, size_t *size)
{
    char *times;
    int e;

    if (len > len + 1 || len == 0)
	return ASN1_BAD_LENGTH;

    times = malloc(len + 1);
    if (times == NULL)
	return ENOMEM;
    memcpy(times, p, len);
    times[len] = '\0';
    e = generalizedtime2time(times, data);
    free (times);
    if(size) *size = len;
    return e;
}