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

/* Variables and functions */
 unsigned int JSON_NoParse (char const*,char const*) ; 
 int /*<<< orphan*/  JSON_ValueGetString (char const*,char const*,char*,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,float*) ; 

float JSON_ValueGetFloat(const char *json, const char *jsonEnd)
{
	char cValue[256];
	float fValue = 0.0f;
	unsigned int np = JSON_NoParse(json, jsonEnd);

	if (np)
		return (float)(np - 1);

	if (!JSON_ValueGetString(json, jsonEnd, cValue, 256))
		return 0.0f;

	sscanf(cValue, "%f", &fValue);

	return fValue;
}