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
typedef  int hx509_prompt_type ;

/* Variables and functions */
#define  HX509_PROMPT_TYPE_INFO 129 
#define  HX509_PROMPT_TYPE_QUESTION 128 

int
hx509_prompt_hidden(hx509_prompt_type type)
{
    /* default to hidden if unknown */

    switch (type) {
    case HX509_PROMPT_TYPE_QUESTION:
    case HX509_PROMPT_TYPE_INFO:
	return 0;
    default:
	return 1;
    }
}