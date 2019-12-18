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
typedef  int /*<<< orphan*/  FilterTypes ;

/* Variables and functions */
 int /*<<< orphan*/  BlackmanFilter ; 
 int /*<<< orphan*/  BoxFilter ; 
 int /*<<< orphan*/  CatromFilter ; 
 int /*<<< orphan*/  CubicFilter ; 
 int /*<<< orphan*/  GaussianFilter ; 
 int /*<<< orphan*/  HanningFilter ; 
 int /*<<< orphan*/  HermiteFilter ; 
 int /*<<< orphan*/  LanczosFilter ; 
 int /*<<< orphan*/  MitchellFilter ; 
 int /*<<< orphan*/  PointFilter ; 
 int /*<<< orphan*/  QuadraticFilter ; 
 int /*<<< orphan*/  SincFilter ; 
 int /*<<< orphan*/  TriangleFilter ; 
 int /*<<< orphan*/  UndefinedFilter ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static FilterTypes get_filter_type (const char* s) {
  switch (*s++) {
  case 'b':
    if (!strcmp ("ox", s)) {
      return BoxFilter;
    }
    if (!strcmp ("lackman", s)) {
      return BlackmanFilter;
    }
    if (!strcmp ("essel", s)) {
      return BlackmanFilter;
    }
    break;
  case 'c':
    if (!strcmp ("ubic", s)) {
      return CubicFilter;
    }
    if (!strcmp ("atrom", s)) {
      return CatromFilter;
    }
    break;
  case 'g':
    if (!strcmp ("aussian", s)) {
      return GaussianFilter;
    }
    break;
  case 'h':
    if (!strcmp ("ermite", s)) {
      return HermiteFilter;
    }
    if (!strcmp ("anning", s)) {
      return HanningFilter;
    }
    break;
  case 'l':
    if (!strcmp ("anczos", s)) {
      return LanczosFilter;
    }
    break;
  case 'm':
    if (!strcmp ("itchell", s)) {
      return MitchellFilter;
    }
    break;
  case 'p':
    if (!strcmp ("oint", s)) {
      return PointFilter;
    }
    break;
  case 'q':
    if (!strcmp ("uadratic", s)) {
      return QuadraticFilter;
    }
    break;
  case 's':
    if (!strcmp ("inc", s)) {
      return SincFilter;
    }
    break;
  case 't':
    if (!strcmp ("riangle", s)) {
      return TriangleFilter;
    }
    break;
  }
  return UndefinedFilter;
}