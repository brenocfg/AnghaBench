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
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_3__ {int const width; int const height; int redBits; int greenBits; int blueBits; int refreshRate; } ;
typedef  TYPE_1__ GLFWvidmode ;

/* Variables and functions */
 int euclid (int const,int const) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int const,int const,int,int const,int const,int,int,int,int) ; 

__attribute__((used)) static const char* format_mode(const GLFWvidmode* mode)
{
    static char buffer[512];
    const int gcd = euclid(mode->width, mode->height);

    snprintf(buffer,
             sizeof(buffer),
             "%i x %i x %i (%i:%i) (%i %i %i) %i Hz",
             mode->width, mode->height,
             mode->redBits + mode->greenBits + mode->blueBits,
             mode->width / gcd, mode->height / gcd,
             mode->redBits, mode->greenBits, mode->blueBits,
             mode->refreshRate);

    buffer[sizeof(buffer) - 1] = '\0';
    return buffer;
}