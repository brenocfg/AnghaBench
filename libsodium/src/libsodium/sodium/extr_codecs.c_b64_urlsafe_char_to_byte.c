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
 int EQ (unsigned int const,char) ; 
 int GE (int,char) ; 
 int LE (int,char) ; 

__attribute__((used)) static unsigned int
b64_urlsafe_char_to_byte(int c)
{
    const unsigned x =
        (GE(c, 'A') & LE(c, 'Z') & (c - 'A')) |
        (GE(c, 'a') & LE(c, 'z') & (c - ('a' - 26))) |
        (GE(c, '0') & LE(c, '9') & (c - ('0' - 52))) | (EQ(c, '-') & 62) |
        (EQ(c, '_') & 63);

    return x | (EQ(x, 0) & (EQ(c, 'A') ^ 0xFF));
}