int
parse_escape (char **string_ptr)
{
  int target_char;
  int c = *(*string_ptr)++;
  if (c_parse_backslash (c, &target_char))
    return target_char;
  else
    switch (c)
      {
      case '\n':
	return -2;
      case 0:
	(*string_ptr)--;
	return 0;
      case '^':
	{
	  /* Remember where this escape sequence started, for reporting
	     errors.  */
	  char *sequence_start_pos = *string_ptr - 1;

	  c = *(*string_ptr)++;

	  if (c == '?')
	    {
	      /* XXXCHARSET: What is `delete' in the host character set?  */
	      c = 0177;

	      if (!host_char_to_target (c, &target_char))
		error ("There is no character corresponding to `Delete' "
		       "in the target character set `%s'.", host_charset ());

	      return target_char;
	    }
	  else if (c == '\\')
	    target_char = parse_escape (string_ptr);
	  else
	    {
	      if (!host_char_to_target (c, &target_char))
		no_control_char_error (sequence_start_pos, *string_ptr);
	    }

	  /* Now target_char is something like `c', and we want to find
	     its control-character equivalent.  */
	  if (!target_char_to_control_char (target_char, &target_char))
	    no_control_char_error (sequence_start_pos, *string_ptr);

	  return target_char;
	}

	/* XXXCHARSET: we need to use isdigit and value-of-digit
	   methods of the host character set here.  */

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
	{
	  int i = c - '0';
	  int count = 0;
	  while (++count < 3)
	    {
	      c = (**string_ptr);
	      if (c >= '0' && c <= '7')
		{
		  (*string_ptr)++;
		  i *= 8;
		  i += c - '0';
		}
	      else
		{
		  break;
		}
	    }
	  return i;
	}
      default:
	if (!host_char_to_target (c, &target_char))
	  error
	    ("The escape sequence `\%c' is equivalent to plain `%c', which"
	     " has no equivalent\n" "in the `%s' character set.", c, c,
	     target_charset ());
	return target_char;
      }
}